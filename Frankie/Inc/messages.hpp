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

#ifndef INC_MESSAGES_HPP_
#define INC_MESSAGES_HPP_

#pragma once

#include "common.hpp"


typedef struct{
	void* body{nullptr};
	bool confirmed{false};
}MessageParam;

using post_t = std::array<MessageParam, MAX_MESSAGE_NUM>;

class Post{

public:

	template <typename T>
	static void push_msg (msg m, T* data){
		base_t idx = static_cast<base_t>(m);

		assert_param( (idx < MAX_MESSAGE_NUM) && (data != nullptr) );

		mbox[idx].confirmed = true;
		mbox[idx].body = static_cast<void*>(data);
	}

	static void push_msg (msg m){
		base_t idx = static_cast<base_t>(m);

		assert_param(idx < MAX_MESSAGE_NUM);

		mbox[idx].confirmed = true;
	}

	static MessageParam& get_msg (msg m){

		base_t idx = static_cast<base_t>(m);

		assert_param(idx < MAX_MESSAGE_NUM);

		res = MessageParam{};

		critical_section lock;

		if (mbox[idx].confirmed){

			std::swap(res, mbox[idx]);
		}

		return res;
	}

	static void clear_box(void){

		res = MessageParam{};

		critical_section lock;

		for (auto& item : mbox){

			item = res;
		}
	}

private:

	Post() = delete;
	Post(const Post&)= delete;
	Post& operator=(const Post&)= delete;

	static post_t mbox;
	static MessageParam res;
};

#endif /* INC_MESSAGES_HPP_ */
