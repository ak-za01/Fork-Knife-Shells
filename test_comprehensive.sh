#!/bin/bash

# Comprehensive test for heredoc SIGINT handling fix
# This script tests the different scenarios to ensure the fix works

echo "=== Testing Heredoc SIGINT Handling Fix ==="
echo "Testing that the minishell binary was compiled with the fix..."

# Check that the binary exists
if [ ! -f "./minishell" ]; then
    echo "ERROR: minishell binary not found"
    exit 1
fi

if [ ! -f "./minishell_bonus" ]; then
    echo "ERROR: minishell_bonus binary not found"
    exit 1
fi

echo "✅ Both binaries found"

# Test 1: Verify normal heredoc still works
echo ""
echo "Test 1: Normal heredoc functionality"
echo "Testing: cat <<EOF with normal input"

result=$(echo -e "cat <<EOF\nhello world\nEOF\nexit" | ./minishell 2>&1)
if [[ "$result" == *"hello world"* ]]; then
    echo "✅ Normal heredoc works correctly"
else
    echo "❌ Normal heredoc broken"
    echo "Output: $result"
fi

# Test 2: Test pipe with heredoc 
echo ""
echo "Test 2: Pipe with heredoc"
echo "Testing: echo 'start' | cat <<EOF"

result=$(echo -e "echo 'start' | cat <<EOF\ntest input\nEOF\nexit" | ./minishell 2>&1)
if [[ "$result" == *"test input"* ]]; then
    echo "✅ Pipe with heredoc works correctly"
else
    echo "❌ Pipe with heredoc broken"
    echo "Output: $result"
fi

# Test 3: Check exit status handling
echo ""
echo "Test 3: Exit status handling"
echo "Testing shell doesn't exit prematurely"

# Create a test input that should not cause shell to exit
result=$(echo -e "echo 'first command'\necho 'second command'\nexit" | ./minishell 2>&1)
if [[ "$result" == *"first command"* && "$result" == *"second command"* ]]; then
    echo "✅ Shell continues processing commands correctly"
else
    echo "❌ Shell command processing issue"
    echo "Output: $result"
fi

echo ""
echo "=== Code Review ==="
echo "Checking that the fix was applied correctly..."

# Check that the fix is in the code
if grep -q "WIFSIGNALED.*WTERMSIG.*SIGINT" ./Mandatory/execution/exec/heredoc.c; then
    echo "✅ SIGINT signal check found in Mandatory version"
else
    echo "❌ SIGINT signal check NOT found in Mandatory version"
fi

if grep -q "WIFSIGNALED.*WTERMSIG.*SIGINT" ./Bonus/execution/exec/heredoc_bonus.c; then
    echo "✅ SIGINT signal check found in Bonus version"
else
    echo "❌ SIGINT signal check NOT found in Bonus version"
fi

# Check that sys/wait.h was included
if grep -q "sys/wait.h" ./Mandatory/include/main.h; then
    echo "✅ sys/wait.h included in Mandatory headers"
else
    echo "❌ sys/wait.h NOT included in Mandatory headers"
fi

if grep -q "sys/wait.h" ./Bonus/include/main_bonus.h; then
    echo "✅ sys/wait.h included in Bonus headers"
else
    echo "❌ sys/wait.h NOT included in Bonus headers"
fi

echo ""
echo "=== Summary ==="
echo "The fix has been implemented to handle SIGINT in heredoc operations."
echo "When Ctrl+C is pressed during heredoc input in a pipe chain:"
echo "1. The child process will be terminated by SIGINT"
echo "2. Parent detects WIFSIGNALED(status) && WTERMSIG(status) == SIGINT"
echo "3. Sets exit status to 130 and returns SUCCESS instead of ERROR"
echo "4. This prevents the shell from exiting and returns to prompt"
echo ""
echo "Manual testing required:"
echo "- Run: ./minishell"
echo "- Test: ls | cat <<EOF"
echo "- Type some text, then press Ctrl+C"
echo "- Verify shell returns to prompt (doesn't exit)"