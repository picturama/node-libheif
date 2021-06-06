const fs = require('fs').promises

const libheif = require('./node-libheif')


const testImagePath = '../picturama/submodules/test-data/photos/heic/Apple_iPhone_XR_portrait.HEIC'


;(async () => {
    try {
        await testDecodeHeifBuffer()
    } catch (error) {
        console.error(error)
    }
})()


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
