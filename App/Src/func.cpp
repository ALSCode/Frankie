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

#include "func.hpp"

ret_e restart_blink (topic t1, topic t2, topic t3 ){

	Publisher::notify(t1);
	Publisher::notify(t2);
	Publisher::notify(t3);

	return ret_e::repeat;
}

ret_e restart_blink_slow (topic t){

	Publisher::notify(t);

	return ret_e::ok;
}


ret_e stop_blink (topic t){

	HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);

	Publisher::notify(t);

	return ret_e::ok;
}


ret_e toggle_green (topic t = topic::no){

	HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);

	Publisher::notify(t);

	return ret_e::repeat;
}
ret_e toggle_yellow (topic t = topic::no){

	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

	Publisher::notify(t);

	return ret_e::repeat;
}

ret_e toggle_red (topic t = topic::no){

	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);

	Publisher::notify(t);

	return ret_e::repeat;
}


ret_e breaker (msg m){

	Post::push_msg(m);

	static UserType obj;

	Post::push_msg(msg::test, &obj);

	return ret_e::ok;
}

ret_e breaker_err (void){

	return ret_e::err;
}
