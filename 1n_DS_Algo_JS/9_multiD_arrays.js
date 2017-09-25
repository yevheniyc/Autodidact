// create matrix with provided initial values
Array.matrix = function(numrows, numcols, initial) {
    var arr = []
    for (var i = 0; i < numrows; i++) {
        var columns = []
        for (var j = 0; j < numcols; ++j) {
            columns[j] = initial;
        }
        arr[i] = columns
    }
    return arr;
}

var nums = Array.matrix(5,5,0)
console.log(nums[1][1]) // 0

var names = Array.matrix(3,3,"");
names[1][2] = "Joe"
console.log(names[1][2]) // Joe

console.log(nums)

////// Multi-D Processing

// accessing array elements by columns
var grades = [[89, 74, 77],
              [76, 82, 81],
              [91, 94, 89]]

var total = 0
var average = 0.0
for (var row = 0; row < grades.length; ++row) {
    for (var col = 0; col < grades[row].length; col++) {
        total += grades[row][col]
    }
    average = total / grades[row].length
    console.log("Student " + parseInt(row + 1) + " average: " +
        average.toFixed(2)
    )
    total = 0
    average = 0.0
}

// accessing array elements by rows
var grades = [[1, 1, 1],
              [0, 0, 0],
              [0, 1, 4]]
var total = 0;
var average = 0.0
for (var col = 0; col < grades.length; col++) {
    for (var row = 0; row < grades[col].length; row++) {
        total += grades[row][col];
    }

    average = total / grades.length;
    
    console.log("Grades " + parseInt(col + 1) + " average: " +
        average.toFixed(2)
    )
    total = 0
    average = 0.0
}


//////// Jagged Arrays - same as accessing elements by columns
var grades = [[89, 77],
              [76, 82, 81],
              [91, 94, 89, 99]];
var total = 0;
var average = 0.0;

for (var row = 0; row < grades.length; ++row) {
    for (var col = 0; col < grades[row].length; ++col) {
        total += grades[row][col];
    }

    average = total / grades[row].length;
    console.log("Student " + parseInt(row+1) + " average: " +
        average.toFixed(2)
    );
    total = 0;
    average = 0.0;
}
