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

#ifndef INC_FW_CPP_
#define INC_FW_CPP_

#pragma once

template <class T>
struct just_type{
	using type = T;
};

template <class... Ts>
struct type_pack{};

template <class... Ts>
constexpr std::size_t size(type_pack<Ts...>){
	return sizeof...(Ts);
}

template <class T, class... Ts>
constexpr std::size_t find(type_pack<Ts...> tp, [[maybe_unused]] just_type<T> t){

	using fsize = std::size_t;
	bool bs[] = {std::is_same_v<T, Ts>...};
	fsize s = size(tp);

	for (fsize i = 0; i != s; ++i){
		if (bs[i]) return i;
	}

	return s;
}


class DeviceImpl;

class Device{

public:
	Device();
	void action(void);

private:
	Device(const Device&)= delete;
	Device& operator=(const Device&)= delete;

	static DeviceImpl& impl(void);
	DeviceImpl& impl_;
};


#endif /* INC_FSM_CPP_ */
