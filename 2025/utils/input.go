// Package utils provides utility functions for file I/O operations
package utils

import (
	"bufio"
	"encoding/csv"
	"fmt"
	"os"
	"strings"
)

func ReadAsLines(fpath string) ([]string, error) {
	file, err := os.Open(fpath)
	if err != nil {
		return nil, err
	}
	defer func() {
		_ = file.Close()
	}()

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

func ReadAsLinesNL(fpath string) ([]string, error) {
	file, err := os.Open(fpath)
	if err != nil {
		return nil, err
	}
	defer func() {
		_ = file.Close()
	}()

	var lines []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()

		// Skip empty lines to prevent "index out of range" later
		if strings.TrimSpace(line) == "\n" {
			lines = append(lines, "")
		}

		lines = append(lines, line)
	}

	if err := scanner.Err(); err != nil {
		return nil, err
	}
	return lines, nil
}

func ReadAsDelimitedLine(fpath string, delimiter rune) ([]string, error) {
	file, err := os.Open(fpath)
	if err != nil {
		return nil, err
	}
	defer func() {
		_ = file.Close()
	}()

	reader := csv.NewReader(file)
	reader.Comma = delimiter

	record, err := reader.Read()
	if err != nil {
		return nil, err
	}

	return record, nil
}

func GetFpath(args []string) (string, error) {
	if len(args) < 2 {
		fmt.Printf("Usage: %s <input.txt>\n", args[0])
		return "", fmt.Errorf("no input file specified")
	}

	return args[1], nil
}

func ReadAsGrid(fpath string) ([][]rune, error) {
	lines, err := ReadAsLines(fpath)
	if err != nil {
		return nil, err
	}

	if len(lines) == 0 {
		return [][]rune{}, nil
	}

	grid := make([][]rune, len(lines))
	for i, line := range lines {
		grid[i] = []rune(line)
	}

	return grid, nil
}
