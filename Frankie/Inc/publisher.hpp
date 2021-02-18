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

#ifndef INC_PUBLISHER_HPP_
#define INC_PUBLISHER_HPP_

#pragma once

#include "common.hpp"

typedef struct {
	base_t top{0};
	base_t status{0};
}Subscription;

using publisher_t = std::array<Subscription, MAX_SUBSCRIPTION_NUM>;

class Publisher{

public:

	static void subscribe (topic t){

		base_t idx = static_cast<base_t>(t);

		assert_param(idx < MAX_SUBSCRIPTION_NUM);

		++(box[idx].top);
	}

	static base_t check_subscription  (topic t){

		base_t idx = static_cast<base_t>(t);

		assert_param(idx < MAX_SUBSCRIPTION_NUM);

		critical_section lock;

		base_t res = box[idx].status;

		if (res) --(box[idx].status);

		return res;
	}

	static void notify (topic t){

		base_t idx = static_cast<base_t>(t);

		assert_param(idx < MAX_SUBSCRIPTION_NUM);

		box[idx].status = box[idx].top;
	}

	static void clear_box (void){

		Subscription zero;

		critical_section lock;

		for (auto& item : box){
			item = zero;
		}
	}

private:
	Publisher() = delete;
	Publisher(const Publisher&)= delete;
	Publisher& operator=(const Publisher&)= delete;

	static publisher_t box;
};

#endif /* INC_PUBLISHER_HPP_ */
