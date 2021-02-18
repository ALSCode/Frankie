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

#include <variant>

#include "frankie.hpp"
#include "states.hpp"


class DeviceImpl{

public:

	using state_p = type_pack<STATES>;
	using state_v = std::variant<STATES>;
	using state_a = std::array<state_v, size(state_p{})>;

	constexpr DeviceImpl() : idx(0) {

		set(state_p{});
	}

private:

	template <class... Ts>
	constexpr void set (type_pack<Ts...>){

		(set_impl(just_type<Ts>{}), ...);
	};


	template <typename T>
	constexpr void set_impl (just_type<T> t){

		using state_t = typename decltype(t)::type;

		std::size_t i = find(state_p{}, t);

		states[i].emplace<state_t>(state_t{});
	}
public:
	state_a states;
	base_t idx;
};

DeviceImpl& Device::impl(void){

	static DeviceImpl instance;
	return instance;
}

Device::Device() : impl_( impl() ){}

void Device::action(void){

	base_t temp_idx;

	auto l = [&temp_idx](auto&& arg) { temp_idx = static_cast<base_t> (arg() ); };

	std::visit(l, impl_.states[impl_.idx]);

	impl_.idx = temp_idx;
}
