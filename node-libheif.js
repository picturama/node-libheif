const nativePart = require('bindings')('node_libheif.node')


function loadHeifFile(fileName) {
    return new Promise(function(resolve, reject) {
        nativePart.loadHeifFile(fileName, function(error, result) {
            if (error) {
                reject(new Error(error))
            } else {
                resolve(result)
            }
        })
    })
}


module.exports = {
    loadHeifFile
}
