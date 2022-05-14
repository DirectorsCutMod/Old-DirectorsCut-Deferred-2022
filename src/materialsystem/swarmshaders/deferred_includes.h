/*
*	The following header has been retroactively applied to all
*	code modified for use in Alien Swarm Deferred in order to
*	comply with its original Apache License 2.0 specification:
*
* 	Copyright 2013 Kristjan Skutta
*
* 	Licensed under the Apache License, Version 2.0 (the "License");
* 	you may not use this file except in compliance with the License.
* 	You may obtain a copy of the License at
*
* 		http://www.apache.org/licenses/LICENSE-2.0
*
* 	Unless required by applicable law or agreed to in writing, software
* 	distributed under the License is distributed on an "AS IS" BASIS,
* 	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* 	See the License for the specific language governing permissions and
* 	limitations under the License.
*/

#ifndef DEFERRED_INCLUDES_H
#define DEFERRED_INCLUDES_H

#include "deferred_global_common.h"

#include "commandbuilder.h"
#include "IDeferredExt.h"

#include "basevsshader.h"
#include "cpp_shader_constant_register_map.h"
#include "mathlib/VMatrix.h"
#include "ConVar.h"

#include "lighting_helper.h"

#include "renderparm.h"

#include "deferred_utility.h"
#include "deferred_context.h"

#include "defpass_gbuffer.h"
#include "defpass_shadow.h"
#include "defpass_composite.h"

#include "lighting_pass_basic.h"
#include "lighting_pass_volum.h"

#endif