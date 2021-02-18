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

#ifndef INC_DEFS_HPP_
#define INC_DEFS_HPP_

#pragma once

#include "bm_chrono.hpp"

using base_t = std::uint32_t;

using bm_clock = BaremetalClock;

#define STATES	SF,SS,ES

constexpr base_t MAX_SUBSCRIPTION_NUM = 8;
constexpr base_t MAX_MESSAGE_NUM = 8;
constexpr base_t MAX_TRACK_NUM = 8;

enum class topic: base_t{
	no,
	green,
	yellow,
	red,
	exit,
};


enum class msg: base_t{
	no,
	stop,
	exit,
	test,
};


typedef struct{
	base_t val{8};
	base_t cnt{15};
}UserType;


#endif /* INC_DEFS_HPP_ */
