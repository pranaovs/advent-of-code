package main

import (
	"fmt"
	"os"

	"aoc2025/utils"
)

func main() {
	fpath, err := utils.GetFpath(os.Args)
	if err != nil {
		fmt.Println("Error getting file path:", err)
		os.Exit(1)
	}

	grid, err := utils.ReadAsGrid(fpath)
	if err != nil {
		fmt.Println("Error reading grid:", err)
		os.Exit(3)
	}

	accessibleCount := 0

	for {
		accessibleCountIter := 0
		for i, row := range grid {
			for j := range row {
				if grid[i][j] == '@' && accessible(grid, i, j) {
					grid[i][j] = '.'
					accessibleCountIter++
				}
			}
		}
		if accessibleCountIter == 0 {
			break
		}
		accessibleCount += accessibleCountIter
	}

	fmt.Println("Accessible @ count:", accessibleCount)
}

func accessible(grid [][]rune, x, y int) bool {
	adjacentGrid := [][2]int{
		{x - 1, y},
		{x + 1, y},
		{x, y - 1},
		{x, y + 1},
		{x + 1, y + 1},
		{x - 1, y - 1},
		{x + 1, y - 1},
		{x - 1, y + 1},
	}

	adjacent := 0

	for _, pos := range adjacentGrid {
		if pos[0] >= 0 && pos[0] < len(grid) && pos[1] >= 0 && pos[1] < len(grid[0]) {
			if grid[pos[0]][pos[1]] == '@' {
				adjacent++
			}
		}
	}
	// println("Position:", x, y, "Adjacent @:", adjacent)
	return adjacent < 4
}
