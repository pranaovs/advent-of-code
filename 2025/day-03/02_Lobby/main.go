package main

import (
	"fmt"
	"os"
	"strconv"

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

	for i := range input {
		val, _ := strconv.Atoi(largestBankJoltage(input[i], 12))
		output += val
		println("Line:", input[i], "->", val)
	}

	fmt.Println("Output:", output)
}

func largestBankJoltage(batteries string, targetLen int) string {
	result := make([]byte, 0, targetLen)
	n := len(batteries)

	for i := 0; i < targetLen; i++ {
		remaining := targetLen - i - 1
		maxDigit := byte('0')
		maxIdx := 0
		for j := 0; j <= n-1-remaining; j++ {
			if batteries[j] > maxDigit {
				maxDigit = batteries[j]
				maxIdx = j
			}
		}
		result = append(result, maxDigit)
		batteries = batteries[maxIdx+1:]
		n = len(batteries)
	}
	return string(result)
}
