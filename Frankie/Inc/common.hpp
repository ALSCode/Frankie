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

#ifndef INC_COMMON_HPP_
#define INC_COMMON_HPP_

#pragma once

#include <array>
#include <type_traits>

#include "defs.hpp"
#include "critical_section.hpp"


enum class States_e : base_t{
	STATES
};


enum class ret_e : base_t{
	ok,
	err,
	repeat,
};


enum class status_e : base_t{
	stopped,
	active,
};


typedef struct {
	base_t entry{0};
	bm_clock::time_point stamp;
}TrackParam;


typedef struct {
	std::array<TrackParam, MAX_TRACK_NUM> tracks;
	base_t failed_track{0};
	base_t cnt{0};
}StateParam;


typedef struct {
	StateParam state;
	status_e status{0};
	States_e current{0};
}DeviceParam;


class DeviceHandler{

public:

	static status_e& get_state_status(void){
		return param.status;
	}

	static void set_state_status(status_e new_status){
		param.status = new_status;
	}

	static void reset_track_cnt(void){
		param.state.cnt = 0;
	}

	static TrackParam& get_track_param (void){
		return param.state.tracks[param.state.cnt++];
	}

	static base_t& get_failed_track(void){
		return param.state.failed_track;
	}

	static void mark_failed_track(void){
		param.state.failed_track = param.state.cnt - 1;
	}

	static void clear_state_param (void){

		critical_section lock;

		param.state.cnt = 0;
		param.state.failed_track = 0;

		for (auto& item : param.state.tracks)
			item.entry = 0;
	}

private:
	DeviceHandler() = delete;
	DeviceHandler(const DeviceHandler&)= delete;
	DeviceHandler& operator=(const DeviceHandler&)= delete;

	static DeviceParam param;
};

#endif /* INC_COMMON_HPP_ */
