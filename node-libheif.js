const nativePart = require('bindings')('node_libheif.node')


function decodeHeifFile(fileName) {
    return new Promise(function(resolve, reject) {
        nativePart.decodeHeifFile(fileName, function(error, result) {
            if (error) {
                reject(new Error(error))
            } else {
                resolve(result)
            }
        })
    })
}


module.exports = {
    decodeHeifFile
}
