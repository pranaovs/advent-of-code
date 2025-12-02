package main

import (
	"encoding/csv"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func readInput(filename string) ([]string, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	reader := csv.NewReader(file)

	record, err := reader.Read()
	if err != nil {
		return nil, err
	}

	return record, nil
}

func getRange(rangeStr string) (string, string, error) {
	parts := strings.Split(rangeStr, "-")
	if len(parts) != 2 {
		return "", "", fmt.Errorf("invalid range format: %s", rangeStr)
	}

	return parts[0], parts[1], nil
}

func detectPattern(snum string) bool {
	if snum[0] == '0' {
		fmt.Printf("%s starts with 0, returning false\n", snum)
		return false
	}

	digits := len(snum)

	if digits%2 != 0 {
		return false
	}

	if snum[0:digits/2] == snum[digits/2:digits] {
		return true
	}

	return false
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

	sum := 0

	for _, rangeStr := range input {
		fmt.Printf("Range: %s\n", rangeStr)
		start, end, err := getRange(rangeStr)
		if err != nil {
			fmt.Printf("Error parsing range '%s': %v\n", rangeStr, err)
			continue
		}

		startNum, _ := strconv.Atoi(start)
		endNum, _ := strconv.Atoi(end)
		for num := startNum; num <= endNum; num++ {
			if detectPattern(strconv.Itoa(num)) {
				fmt.Printf("Found pattern number: %d\n", num)
				sum += num
			}
		}
	}

	fmt.Printf("Total Sum: %d\n", sum)
}
