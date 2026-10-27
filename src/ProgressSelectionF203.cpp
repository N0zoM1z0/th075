// Source-compatible borrowed game progress / completion record view.
// Neither this receiver nor the encoded record storage is instantiated.
class ProgressArchiveF203 {
public:
    unsigned char QueryEntry(int index);
};
extern ProgressArchiveF203 g_ProgressArchiveAt006718F8;

namespace GameProgressF203 {
unsigned char CheckSelection(signed char selection, signed char mode)
{
    unsigned char matches = 1;
    int i;
    if (mode == 0) {
        switch (selection) {
        case 6:
            matches = 0;
            matches = matches | (g_ProgressArchiveAt006718F8.QueryEntry(0) |
                       g_ProgressArchiveAt006718F8.QueryEntry(20) |
                       g_ProgressArchiveAt006718F8.QueryEntry(40));
            matches = matches | (g_ProgressArchiveAt006718F8.QueryEntry(1) |
                       g_ProgressArchiveAt006718F8.QueryEntry(21) |
                       g_ProgressArchiveAt006718F8.QueryEntry(41));
            matches = matches | (g_ProgressArchiveAt006718F8.QueryEntry(5) |
                       g_ProgressArchiveAt006718F8.QueryEntry(25) |
                       g_ProgressArchiveAt006718F8.QueryEntry(45));
            break;
        case 7:
            matches = 0;
            matches = matches | (g_ProgressArchiveAt006718F8.QueryEntry(2) |
                       g_ProgressArchiveAt006718F8.QueryEntry(22) |
                       g_ProgressArchiveAt006718F8.QueryEntry(42));
            matches = matches | (g_ProgressArchiveAt006718F8.QueryEntry(4) |
                       g_ProgressArchiveAt006718F8.QueryEntry(24) |
                       g_ProgressArchiveAt006718F8.QueryEntry(44));
            break;
        case 8:
            matches = 0;
            for (i = 0; i < 6; ++i)
                matches = matches | (g_ProgressArchiveAt006718F8.QueryEntry(i + 20) |
                           g_ProgressArchiveAt006718F8.QueryEntry(i + 40));
            break;
        case 9:
        case 10:
            matches = 0;
            for (i = 0; i < 6; ++i)
                matches = matches | (g_ProgressArchiveAt006718F8.QueryEntry(i + 40));
            break;
        }
    } else {
        switch (selection) {
        case 6:
        case 7:
            for (i = 0; i < 6; ++i)
                matches = matches & (g_ProgressArchiveAt006718F8.QueryEntry(i + 40));
            break;
        case 8:
            matches = g_ProgressArchiveAt006718F8.QueryEntry(46) &
                      g_ProgressArchiveAt006718F8.QueryEntry(47);
            break;
        case 9:
            matches = g_ProgressArchiveAt006718F8.QueryEntry(48);
            break;
        case 10:
            matches = 0;
            break;
        }
    }
    return matches;
}
}
