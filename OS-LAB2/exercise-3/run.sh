# chmod +x run.sh
# before ./run.sh

set -e

echo "Clean Build"
make clean

echo "Build All"
make all

echo "Running..."
./ex3
