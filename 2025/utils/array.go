package utils

func TransposeGridString(input [][]string) [][]string {
	if len(input) == 0 || len(input[0]) == 0 {
		return [][]string{}
	}

	rows := len(input)
	cols := len(input[0])

	transposed := make([][]string, cols)
	for i := range transposed {
		transposed[i] = make([]string, rows)
	}

	for i := range rows {
		for j := range cols {
			transposed[j][i] = input[i][j]
		}
	}

	return transposed
}
