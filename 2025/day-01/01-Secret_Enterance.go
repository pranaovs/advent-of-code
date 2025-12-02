//go:build part1

package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func left(dial, count int) int {
	return (dial - count) % 100
}

func right(dial, count int) int {
	return (dial + count) % 100
}

func readInput(path string) ([]string, error) {
	file, err := os.Open(path)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	var lines []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()

		// Skip empty lines to prevent "index out of range" later
		if strings.TrimSpace(line) == "" {
			continue
		}

		lines = append(lines, line)
	}

	if err := scanner.Err(); err != nil {
		return nil, err
	}
	return lines, nil
}

func main() {
	if len(os.Args) < 2 {
		fmt.Printf("Usage: %s <input.txt>\n", os.Args[0])
		os.Exit(1)
	}

	filename := os.Args[1]
	input, err := readInput(filename)
	if err != nil {
		fmt.Printf("Error reading input file: %v\n", err)
		os.Exit(2)
	}

	dial := 50
	password := 0

	for _, word := range input {
		direction := word[0]
		distance, err := strconv.Atoi(word[1:])
		if err != nil {
			fmt.Printf("Error parsing distance: %v\n", err)
			continue
		}
		switch direction {
		case 'L':
			dial = left(dial, distance)
		case 'R':
			dial = right(dial, distance)
		default:
			fmt.Printf("Unknown direction: %c\n", direction)
		}

		if dial == 0 {
			password++
		}
	}

	fmt.Printf("Password: %d\n", password)
}
