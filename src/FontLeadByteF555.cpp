// Complete original 0041CA30..0041CA7C: policy for Shift-JIS lead-byte ranges.
// Provisional borrowed owner ABI inferred from the exact parent 0041C9D0.
// No source-level ownership of the full FontSurface class is claimed.
class PackedFontUnitF293 {
public:
    bool IsDoubleByte(char lead);
};

bool PackedFontUnitF293::IsDoubleByte(char lead) {
    if (static_cast<unsigned char>(lead) < 0x81) return false;
    if (static_cast<unsigned char>(lead) < 0xA0) return true;
    if (static_cast<unsigned char>(lead) < 0xE0) return false;
    if (static_cast<unsigned char>(lead) < 0xFF) return true;
    return false;
}
