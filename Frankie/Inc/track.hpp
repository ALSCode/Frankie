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

#ifndef INC_TRACK_HPP_
#define INC_TRACK_HPP_

#pragma once

#include "publisher.hpp"


template<topic N, base_t T, auto* Func>
struct Track{

	static_assert( !std::is_null_pointer_v<decltype(Func)> );

	template<typename... Args>
	static void go (Args... args){

		ret_e res = ret_e::err;
		bm_clock::duration dur;

		TrackParam& p = DeviceHandler::get_track_param();

 		switch (p.entry){

		case 0:

			if (N != topic::no) {

				Publisher::subscribe(N);

				p.entry = 1;

			} else if (T) {

				p.stamp = bm_clock::now();

				p.entry = 2;

			} else {

				p.entry = 3;
			}

			break;

		case 1:

			if ( Publisher::check_subscription(N) ) {

				p.stamp = bm_clock::now();

				p.entry = 2;
			};

			break;

		case 2:

			dur = bm_clock::now() - p.stamp;

			if (dur.count() > T) p.entry = 3;

			break;

		case 3:

			res = (*Func)(args...);

			if (ret_e::repeat == res){

				if (N != topic::no) {

					p.entry = 1;

				} else {

					p.entry = 0;
				}

				break;

			} else if (ret_e::err == res){

				DeviceHandler::mark_failed_track();
			}

			p.entry = 4;

			break;

		case 4:
			__NOP();
			break;

		default:
			break;
		}
	}
};

#endif /* INC_TRACK_HPP_ */
