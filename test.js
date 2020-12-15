const libheif = require('./node-libheif')

const startTime = Date.now()
libheif.loadHeifFile('../test-data/photos/heic/Apple_iPhone_XR_portrait.HEIC')
    .then(image => {
        console.log(`loadHeifFile took ${Date.now() - startTime} ms - image`, image)
    })
    .catch(error => {
        console.error(`Calling loadHeifFile failed after ${Date.now() - startTime} ms`, error)
    })

console.log(`After calling loadHeifFile (${Date.now() - startTime} ms)`)
