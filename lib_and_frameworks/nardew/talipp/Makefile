# file: Makefile
# date: 2022-06-20


.RECIPEPREFIX := $(.RECIPEPREFIX) 


PREPROCESS:=$(rm -rf ./_pyenv)
INIT:=$(python3 -m venv ./_pyenv --copies)
ACTIVATE:=$(source ./_pyenv/bin/activate)
UPGRADE:=$(python -m pip install --upgrade pip)
BUILD:=$(python -m pip install -r ./requirements.txt )

all:
    @echo $(PREPROCESS)
    @echo $(INIT)
    @echo $(ACTIVATE)
    @echo $(UPGRADE)
    @echo $(BUILD)
