/*****************************************************************************
* Author		: Aleksandr Sazhin
* Date		: 2021
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
* Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
*
* Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/

#ifndef INC_STATES_HPP_
#define INC_STATES_HPP_

#pragma once


#include "state.hpp"
#include "func.hpp"

class StateSlow final: public StateInterface<StateSlow> {

private:

	void on_enter_impl (void) {}

	void tracks_go_impl (void) {

		Track<topic::no, 500, restart_blink_slow>::go(topic::green);

		Track<topic::green, 250, toggle_green>::go(topic::yellow);
		Track<topic::yellow, 250, toggle_yellow>::go(topic::red);
		Track<topic::red, 250, toggle_red>::go(topic::green);

		Track<topic::no, 5000, stop_blink>::go(topic::exit);

		Track<topic::exit, 0, breaker_err>::go();

	}

	States_e on_exit_impl (void) {

		States_e next_state = States_e::SS;

		if ( DeviceHandler::get_failed_track() ){

			next_state = States_e::ES;

		} else if ( Post::get_msg(msg::exit).confirmed ) {

			next_state = States_e::SF;
		}

		if (next_state != States_e::SS){

			DeviceHandler::set_state_status(status_e::stopped);
		}

		return next_state;
	}

	friend class StateInterface<StateSlow>;
};

using SS = StateInterface<StateSlow>;



class StateFast final: public StateInterface<StateFast> {

private:

	void on_enter_impl (void) {}

	void tracks_go_impl (void) {

		Track<topic::no, 250, restart_blink>::go(topic::green, topic::yellow, topic::red);

		Track<topic::red, 75, toggle_red>::go(topic::no);
		Track<topic::yellow, 125, toggle_yellow>::go(topic::no);
		Track<topic::green, 250, toggle_green>::go(topic::no);

		Track<topic::no, 3000, stop_blink>::go(topic::exit);

		Track<topic::exit, 0 , breaker>::go(msg::exit);
	}

	States_e on_exit_impl (void) {

		States_e next_state = States_e::SF;

		if ( DeviceHandler::get_failed_track() ) {

			next_state = States_e::ES;

		} else if ( Post::get_msg(msg::exit).confirmed ){

			next_state = States_e::SS;
		}

		if (next_state != States_e::SF){

			DeviceHandler::set_state_status(status_e::stopped);
		}

		return next_state;
	}

	friend class StateInterface<StateFast>;
};

using SF = StateInterface<StateFast>;


class ErrorState final: public StateInterface<ErrorState> {

private:

//	void on_enter_impl (void) {} UNUSED

	void tracks_go_impl (void) {

		Track<topic::no, 150, toggle_red>::go(topic::no);
		Track<topic::no, 3000, stop_blink>::go(topic::exit);
		Track<topic::exit, 0 , breaker>::go(msg::exit);

	}

	States_e on_exit_impl (void) {

		if ( Post::get_msg(msg::exit).confirmed ){

			DeviceHandler::set_state_status(status_e::stopped);

			auto msg = Post::get_msg(msg::test);

			if ( msg.confirmed ) {

				UserType* ptr = static_cast<UserType*>(msg.body);

				if ( (ptr->val == 8) && (ptr->cnt == 15) )

					return States_e::SF;
			}
		}

		return States_e::ES;
	}

	friend class StateInterface<ErrorState>;
};

using ES = StateInterface<ErrorState>;

#endif /* INC_STATES_HPP_ */
