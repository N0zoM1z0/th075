#ifndef TH075_DIAGNOSTIC_LOG_HPP
#define TH075_DIAGNOSTIC_LOG_HPP

namespace DiagnosticLog
{
    void InitializeFile(const char *path);
    void AppendString(const char *message);
    void AppendInteger(int value);
    void AppendFloat(float value);
}

#endif
