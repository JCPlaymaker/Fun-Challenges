# 📁 Description
This steganography challenge presents participants with a corrupted JPEG file. At first glance, the file appears unreadable and fails to open using typical image viewers or standard forensic tools. However, careful byte-level analysis reveals that the image was deliberately obfuscated using multiple reversible transformations inspired by the structure of the Force... and the wisdom of Master Yoda.

# 🧩 Technical Breakdown
The encryption process consists of three layers of obfuscation:

## 1. XOR Encryption (Key: "Yoda")
   
Each byte of the image is XOR’d with a repeating 4-byte key: "Yoda". This step obscures readable headers and makes magic bytes (like 0xFF 0xD8) unrecognizable.

## 2. 4-Byte Block Reordering
   
The image is split into 4-byte blocks. Within each block, the first two bytes are swapped with the last two, effectively turning [A B C D] into [C D A B].

## 3. Byte Pair Swapping
   
Finally, every pair of adjacent bytes is swapped — [x y] → [y x]. This adds a final layer of confusion, especially when viewing the file in a hex editor.

