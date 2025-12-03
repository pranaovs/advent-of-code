package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"

	"aoc2025/utils"
)

func main() {
	fpath, err := utils.GetFpath(os.Args)
	if err != nil {
		fmt.Println("Error getting file path:", err)
		os.Exit(1)
	}

	input, err := utils.ReadAsLines(fpath)
	if err != nil {
		fmt.Println("Error reading input file:", err)
		os.Exit(2)
	}

	output := 0

	for _, bank := range input {
		first, second := largestBankJoltage(bank)
		largestJoltage := first*10 + second
		output += largestJoltage
	}

	fmt.Println("Output:", output)
}

func largestBankJoltage(batteries string) (int, int) {
	for i := 9; i >= 0; i-- {
		firstpos := strings.Index(batteries, strconv.Itoa(i)) // First occurrence of a number
		// fmt.Println("first pos:", firstpos)
		if firstpos == -1 {
			continue
		}
		// largest first number
		first, err := strconv.Atoi(string(rune(batteries[firstpos])))
		if err != nil {
			return -1, -1
		}
		if firstpos != len(batteries)-1 {
			for j := 9; j >= 0; j-- {
				secondpos := strings.Index(batteries[firstpos+1:], strconv.Itoa(j)) // First occurrence of a number in the substr
				// fmt.Println("  second pos:", secondpos)
				if secondpos == -1 {
					continue
				}
				// largest second number
				second, err := strconv.Atoi(string(rune(batteries[firstpos+1:][secondpos])))
				if err != nil {
					return -1, -1
				}
				// if found
				if secondpos != -1 {
					return first, second
				}
			}
		}
	}
	return -1, -1
}
