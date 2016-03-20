#pragma once

#include "ofLog.h"

#ifndef __func__
#define __func__ __FUNCTION__
#endif
#define OFXSQUASHBUDDIES_NOTICE ofLogNotice(string(__func__))
#define OFXSQUASHBUDDIES_WARNING ofLogWarning(string(__func__))
#define OFXSQUASHBUDDIES_ERROR ofLogError(string(__func__))
#define OFXSQUASHBUDDIES_FATAL ofLogFatalError(string(__func__))