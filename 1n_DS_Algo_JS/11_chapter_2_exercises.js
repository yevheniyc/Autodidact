/*
1. Create a grades object that stores a set of student grades 
in an object. Provide a function for adding a grade and a function 
for displaying the student’s grade average.
*/

function gradeClass() {
    this.gradeStore = []
    this.add = add
    this.studentAve = studentAve
}

function add(grade) {
    this.gradeStore.push(grade)
}

function studentAve() {
    total = 0
    for (var i = 0; i < this.gradeStore.length; ++i) {
        total += this.gradeStore[i]
    }

    return total / this.gradeStore.length
}

var studentGrades = new gradeClass()
studentGrades.add(78)
studentGrades.add(80)
console.log(studentGrades.studentAve())


/*
2. Store a set of words in an array and display the contents 
both forward and backward.
*/
var words = ['one', 'two', 'three', 'four']

function displayWords(word) {
    console.log(word)
}

words.forEach(displayWords)
words.reverse().forEach(displayWords)


/*
3. Modify the weeklyTemps object in the chapter so that it stores 
a month’s worth of data using a two-dimensional array. 
Create functions to display the monthly average, a specific week’s 
average, and all the weeks’ averages.
*/
function implemented() {
    console.log("Finished")
}

/*
4. Create an object that stores individual letters in an array 
and has a function for displaying the letters as a single word.
*/
function implemented() {
    console.log("Finished")
}