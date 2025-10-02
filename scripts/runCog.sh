#!/bin/zsh
script_dir=$(dirname $(realpath "$0"))

cd "$script_dir/.."
if [ ! -d ".venv" ]; then
    python3 -m venv .venv
    source .venv/bin/activate
    pip install cogapp Jinja2
else
    source .venv/bin/activate
fi


# cd "$script_dir/.."
# cd Bal/RtMidiRouterLib/MidiClient/genPrpt
# cog -r *.hpp


