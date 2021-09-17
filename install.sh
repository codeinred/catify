#!/bin/bash

cd "$(dirname $0)"

mkdir -p ~/.local/git-hooks
cp bin/catify ~/.local/git-hooks/prepare-commit-msg
