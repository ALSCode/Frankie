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

#ifndef INC_STATE_HPP_
#define INC_STATE_HPP_


#pragma once

#include "track.hpp"
#include "messages.hpp"

template <typename T>
class StateInterface{

public:

	using derived_t = T;
	using derived_ptr = T*;

	StateInterface(){}

	States_e operator() (void){

		on_enter();

		tracks_go();

		return on_exit();
	};

private:

	derived_ptr derived(void){
		return static_cast<derived_ptr>(this);
	}

	void on_enter_impl (void){}

	void tracks_go_impl (void){}

	void on_enter_base (void){
		derived()->on_enter_impl();
	}

	States_e on_exit_base (void) {

		return derived()->on_exit_impl();
	}

	void on_enter (void) {


		if (DeviceHandler::get_state_status() == status_e::stopped){


			Publisher::clear_box();

			Post::clear_box();

			DeviceHandler::clear_state_param();

			DeviceHandler::set_state_status(status_e::active);

			derived()->on_enter_base();
		}
	}

	void tracks_go (void) {
		derived()->tracks_go_impl();
	}

	States_e on_exit (void) {

		DeviceHandler::reset_track_cnt();

		return derived()->on_exit_base();
	}
};

#endif /* INC_STATE_HPP_ */
