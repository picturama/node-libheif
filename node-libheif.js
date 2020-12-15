let nativePart
if (process.env.DEBUG) {
    nativePart = require('./build/Debug/node_libheif.node')
} else {
    nativePart = require('./build/Release/node_libheif.node')
}


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
