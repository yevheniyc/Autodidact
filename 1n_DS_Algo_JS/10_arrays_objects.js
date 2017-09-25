//// Arrays of Objects

function Point(x, y) {
    // build a construct
    this.x = x,
    this.y = y
}

function displayPts(arr) {
    // display properties of object in an array
    for (var i = 0; i < arr.length; ++i) {
        console.log(arr[i].x + ", " + arr[i].y)
    }
}

var p1 = new Point(1, 2)
var p2 = new Point(3, 4)
var p3 = new Point(5, 6)
var points = [p1, p2, p3]
for (var i = 0; i < points.length; i++) {
    console.log("Point " + parseInt(i+1) + ": " + points[i].x 
                + ", " + points[i].y)
}


//// Arrays in Objects
/*  
    Class object with an underlying array used to store data, with
    add and average methods
*/

function weekTemps() {
    this.dataStore = []
    this.add = add
    this.average = average
}

function add(temp) {
    this.dataStore.push(temp)
}

function average() {
    var total = 0
    for (var i = 0; i < this.dataStore.length; ++i) {
        total += this.dataStore[i]
    }
    return total / this.dataStore.length
}

var thisWeek = new weekTemps()
thisWeek.add(52)
thisWeek.add(53)
console.log(thisWeek.average())