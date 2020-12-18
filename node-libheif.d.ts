export interface DecodedHeifImage {
    /** The width of the image (in px) */
    width: number
    /** The height of the image (in px) */
    height: number
    /** The image data in RGB (8 bit per channel). size in bytes = 3 * width * height */
    data: Buffer
}

export function decodeHeifBuffer(buffer: Buffer): Promise<DecodedHeifImage>
