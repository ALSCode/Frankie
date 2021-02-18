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

#ifndef CRITICAL_SECTION_HPP_
#define CRITICAL_SECTION_HPP_

#pragma once

#include "core_cm7.h"


static inline void disable_irq (std::uint32_t primask){
	primask = __get_PRIMASK();
	__disable_irq();
}

static inline void enable_irq (std::uint32_t primask){
	__set_PRIMASK(primask);
	__enable_irq();
}

class SynchroObject{

public:
	void get(void){
		disable_irq (primask_bit);
	}

	void release(void){
		enable_irq (primask_bit);
	}

private:
	std::uint32_t primask_bit;
};


template<class Mutex>
class CriticalSection{

	using mutex = Mutex;

public:
	CriticalSection(){
		m.get();
	}

	~CriticalSection(){
		m.release();
	}

private:
	mutex m;
};

using critical_section = CriticalSection<SynchroObject>;

#endif /* CRITICAL_SECTION_HPP_ */
