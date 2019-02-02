//      atmega-timers.c
//
//      Copyright 2011 Javier Valencia <javiervalencia80@gmail.com>
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//
//

#include "timers.h"
 

void (*_t0_func)();
void (*_t1_func)();
void (*_t2_func)();

void timer0(uint8_t prescaler, uint8_t ticks, void (*f)()) {
	TIMSK &= ~(_BV(OCIE0));				// disable interrupt
	_t0_func = f;						// assign user function
	OCR0 = ticks;						// set top value
	TCCR0 = _BV(WGM01);				// set CTC mode
	TCCR0 = prescaler;					// set prescaler
	TCNT0 = 0;							// reset TCNT counter register
	TIMSK |= _BV(OCIE0);				// enable interrupt
}

void timer0_stop() {
	TCCR0 = 0;							// set prescaler to none, disabling timer
	_t0_func = NULL;
}

#ifdef ENABLE_TIMER0
ISR(TIMER0_COMP_vect) {
	
	if (_t0_func!=NULL)
	{
		_t0_func();
	}
}
#endif

void timer1(uint8_t prescaler, uint16_t ticks, void (*f)()) {
	TIMSK &= ~(_BV(OCIE1A));
	_t1_func = f;
	OCR1A = ticks;
	TCCR1A = 0;
	TCCR1B = prescaler | _BV(WGM12);
	TCNT1 = 0;
	TIMSK |= _BV(OCIE1A);
}

void timer1_stop() {
	TCCR1B = 0;
	_t1_func = NULL;
}

#ifdef ENABLE_TIMER1
ISR(TIMER1_COMPA_vect) {
	
	if (_t1_func!=NULL)
	{
		_t1_func();
	}
}
#endif

void timer2(uint8_t prescaler, uint8_t ticks, void (*f)()) {
	TIMSK &= ~(_BV(OCIE2));
	_t2_func = f;
	OCR2 = ticks;
	ASSR = 0;
	TCCR2 = _BV(WGM21);
	TCCR2 = prescaler;
	TCNT2 = 0;
	TIMSK |= _BV(OCIE2);
}

void timer2_stop() {
 
	TCCR2 = 0;
	_t2_func =NULL;
}

#ifdef ENABLE_TIMER2
ISR(TIMER2_COMP_vect) {
	
	if (_t2_func !=NULL)
	{
		_t2_func();
	}
}
#endif

void wait0(uint8_t prescaler, uint8_t ticks) {
	if (ticks == 0)
	return;						// return if no ticks to count
	TIMSK &= ~(_BV(OCIE0));			// disable compare interrupt
	OCR0 = ticks;					// set top value
	TCCR0 = _BV(WGM01);			// set CTC mode
	TCCR0 = prescaler;				// set prescaler
	TCNT0 = 0;						// reset TCNT counter register
	TIFR |= _BV(OCF0);			// reset compare flag
	while(!(TIFR & _BV(OCF0)));	// wait till compare flag goes up
	TCCR0 = 0;						// stop timer to save energy
}

void wait1(uint8_t prescaler, uint16_t ticks) {
	if (ticks == 0)
	return;
	TIMSK &= ~(_BV(OCIE1A));
	OCR1A = ticks;
	TCCR1A = 0;
	TCCR1B = prescaler | _BV(WGM12);
	TCNT1 = 0;
	TIFR |= _BV(OCF1A);
	while(!(TIFR & _BV(OCF1A)));
	TCCR1B = 0;
}

void wait2(uint8_t prescaler, uint8_t ticks) {
	if (ticks == 0)
	return;
	TIMSK &= ~(_BV(OCIE2));
	ASSR = 0;
	OCR2 = ticks;
	TCCR2 = _BV(WGM21);
	TCCR2 = prescaler;
	TCNT2 = 0;
	TIFR |= _BV(OCF2);
	while(!(TIFR & _BV(OCF2)));
	TCCR2 = 0;
}
