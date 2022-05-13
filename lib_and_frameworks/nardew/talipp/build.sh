
set -x

rm -rf ./_pyenv
python3 -m venv ./_pyenv --copies
source ./_pyenv/bin/activate
python -m pip install --upgrade pip
python -m pip install -r ./requirements.txt
