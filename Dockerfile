FROM ubuntu:22.04

# Avoid interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install required dependencies
RUN apt-get update && apt-get install -y \
    flex \
    bison \
    build-essential \
    make \
    gcc \
    bash \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy the project files into the container
COPY . .

# Create a script to run the tests
RUN echo '#!/bin/bash \n\
set -e \n\
\n\
# Navigate to compiler directory and build \n\
cd /app/compiler-source \n\
echo "Building compiler..." \n\
make clean \n\
make \n\
\n\
# Function to run a single test and print details \n\
run_test() { \n\
    local test_dir=$1 \n\
    local test_name=$(basename "$test_dir") \n\
    local test_file="${test_dir}/${test_name}.c" \n\
    local expected_file="${test_dir}/${test_name}_expected.txt" \n\
    local output_file="/tmp/${test_name}_output.txt" \n\
\n\
    echo "=======================================================" \n\
    echo "Running test: $test_name" \n\
    echo "=======================================================" \n\
    echo "INPUT:" \n\
    cat "$test_file" \n\
    echo "\nEXPECTED OUTPUT:" \n\
    cat "$expected_file" \n\
\n\
    # Run test and capture output \n\
    ./compilador < "$test_file" > "$output_file" 2>&1 \n\
    exit_code=$? \n\
\n\
    echo "\nACTUAL OUTPUT:" \n\
    cat "$output_file" \n\
\n\
    # Compare expected and actual output \n\
    if diff -w "$expected_file" "$output_file" > /dev/null; then \n\
        echo "\n✅ TEST PASSED: $test_name" \n\
    else \n\
        echo "\n❌ TEST FAILED: $test_name" \n\
        echo "DIFFERENCES:" \n\
        diff -w "$expected_file" "$output_file" || true \n\
    fi \n\
    echo "" \n\
    return $exit_code \n\
} \n\
\n\
# Find all test directories and run each test \n\
echo "Finding all tests..." \n\
test_dirs=($(find "./tests" -mindepth 1 -maxdepth 1 -type d)) \n\
\n\
total_tests=${#test_dirs[@]} \n\
passed_tests=0 \n\
failed_tests=0 \n\
\n\
for test_dir in "${test_dirs[@]}"; do \n\
    if run_test "$test_dir"; then \n\
        passed_tests=$((passed_tests + 1)) \n\
    else \n\
        failed_tests=$((failed_tests + 1)) \n\
    fi \n\
done \n\
\n\
# Print summary \n\
echo "=======================================================" \n\
echo "TEST SUMMARY" \n\
echo "=======================================================" \n\
echo "Total tests: $total_tests" \n\
echo "Passed tests: $passed_tests" \n\
echo "Failed tests: $failed_tests" \n\
\n\
# Set exit code based on test results \n\
if [ "$failed_tests" -eq 0 ]; then \n\
    echo "All tests passed!" \n\
    exit 0 \n\
else \n\
    echo "Some tests failed!" \n\
    exit 1 \n\
fi \n\
' > /app/run_tests.sh && chmod +x /app/run_tests.sh

# Default command to run when the container starts
CMD ["/app/run_tests.sh"]
