#!/bin/bash

set -ex

glad --out-path="$PWD" --api gl:core,gles2,vulkan,egl,glx,wgl --merge c --alias --loader --mx --mx-global
