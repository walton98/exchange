#!/bin/bash
git ls-files '*.?pp' | xargs clang-format -i
