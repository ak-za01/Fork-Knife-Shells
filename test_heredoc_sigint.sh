#!/bin/bash

# Test script for heredoc SIGINT handling fix
# Tests both cases: heredoc at start vs heredoc at end of pipe chain

echo "=== Testing heredoc SIGINT handling ==="

# Test case 1: heredoc at the start (should work correctly - baseline)
echo "Test 1: heredoc at start of pipe chain"
echo "Expected: Ctrl+C should return to prompt gracefully"
echo "Commands to run manually:"
echo "  ./minishell"
echo "  <<EOF | cat"
echo "  (type some text, then press Ctrl+C)"
echo ""

# Test case 2: heredoc at the end (the bug we're fixing) 
echo "Test 2: heredoc at end of pipe chain"
echo "Expected: Ctrl+C should return to prompt gracefully (should not exit shell)"
echo "Commands to run manually:"
echo "  ./minishell"
echo "  ls | cat <<EOF"
echo "  (type some text, then press Ctrl+C)"
echo ""

# Test case 3: heredoc in the middle
echo "Test 3: heredoc in middle of pipe chain"
echo "Expected: Ctrl+C should return to prompt gracefully (should not exit shell)"
echo "Commands to run manually:"
echo "  ./minishell"
echo "  echo 'start' | cat <<EOF | wc -l"
echo "  (type some text, then press Ctrl+C)"
echo ""

echo "=== Manual Test Instructions ==="
echo "1. Run: ./minishell"
echo "2. Try each test case above"
echo "3. For each case, verify that pressing Ctrl+C during heredoc input:"
echo "   - Does NOT exit the shell"
echo "   - Returns to the minishell prompt"
echo "   - Sets exit status to 130 (standard for SIGINT)"

echo ""
echo "To run the shell: ./minishell"