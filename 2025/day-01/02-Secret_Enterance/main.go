package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

func left(dial, count int) (int, int) {
	// fmt.Printf("Left: Dial=%d, Count=%d\n", dial, count)

	startVal := float64(dial - 1)
	endVal := float64(dial - count - 1)
	clicks := int(math.Floor(startVal/100.0) - math.Floor(endVal/100.0))
	finalPos := ((dial-count)%100 + 100) % 100

	// fmt.Printf("Clicks: %d\n", clicks)
	return finalPos, clicks
}

func right(dial, count int) (int, int) {
	// fmt.Printf("Right: Dial=%d, Count=%d\n", dial, count)

	startVal := float64(dial)
	endVal := float64(dial + count)
	clicks := int(math.Floor(endVal/100.0) - math.Floor(startVal/100.0))
	finalPos := ((dial+count)%100 + 100) % 100

	// fmt.Printf("Clicks: %d\n", clicks)
	return finalPos, clicks
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
	count := 0
	c := 0

	for _, word := range input {
		direction := word[0]
		distance, err := strconv.Atoi(word[1:])
		if err != nil {
			fmt.Printf("Error parsing distance: %v\n", err)
			continue
		}
		switch direction {
		case 'L':
			dial, c = left(dial, distance)
			count += c
		case 'R':
			dial, c = right(dial, distance)
			count += c
		default:
			fmt.Printf("Unknown direction: %c\n", direction)
		}

		if dial == 0 {
			password++
		}
	}

	fmt.Printf("Password: %d\n", password)
	fmt.Printf("Total Clicks: %d\n", count)
}
