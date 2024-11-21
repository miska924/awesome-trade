#pragma once

#define UNUSED(x) (void)(x)

#ifdef DEBUG
#define ON_DEBUG(x) x
#else
#define ON_DEBUG(x)
#endif