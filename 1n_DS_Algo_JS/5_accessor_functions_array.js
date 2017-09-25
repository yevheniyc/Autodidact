// Accessor functions

// 1. indexOf/lastIndexOf()
var names = ['one', 'two', 'three']
var pos = names.indexOf('one')

if (pos >= 0) {
    console.log("found " + "one" + " at pos: " + pos)
} else {
    console.log('one' + ' not found in array: ', names)
}

// 2. toString()/join()
var namestr = names.join()
var namearray = namestr.toString()

// 3. concat(), splice()
new_string = namestr.concat('hello you...')
new_spliced_string = new_string.slice(5, 3) // .splice(start_pos, num_of_elem)
console.log('Spliced 3 elements at pos: 5: ', new_spliced_string)
