const fs = require('fs').promises

const libheif = require('./node-libheif')


const testImagePath = '../test-data/photos/heic/Apple_iPhone_XR_portrait.HEIC';


(async () => {
    try {
        // Load image once before tests, so it is already in I/O cache and we get comparable results
        await fs.readFile(testImagePath)

        await testDecodeHeifFile()
        await testDecodeHeifBuffer()
    } catch (error) {
        console.error(error)
    }
})()


async function testDecodeHeifFile() {
    const startTime = Date.now()
    const promise = libheif.decodeHeifFile(testImagePath)
    console.log(`After calling decodeHeifFile (${Date.now() - startTime} ms)`)
    const image = await promise
    console.log(`decodeHeifFile took ${Date.now() - startTime} ms - image`, image)
}


async function testDecodeHeifBuffer() {
    const startReadFile = Date.now()
    const buffer = await fs.readFile(testImagePath)
    console.log(`Loading file via node took ${Date.now() - startReadFile} ms`)

    const startTime = Date.now()
    const promise = libheif.decodeHeifBuffer(buffer)
    console.log(`After calling decodeHeifBuffer (${Date.now() - startTime} ms)`)
    const image = await promise
    console.log(`decodeHeifBuffer took ${Date.now() - startTime} ms - image`, image)
}
