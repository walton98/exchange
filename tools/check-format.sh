#!/bin/bash
git ls-files '*.?pp' | xargs clang-format -n -Werror
