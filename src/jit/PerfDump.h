/*
 * Copyright (c) 2024-present Samsung Electronics Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if defined WALRUS_JITPERF
#ifndef __WalrusJITPERF__
#define __WalrusJITPERF_

#include <sys/time.h>
#include <ctime>
#include <cstdint>
#include <elf.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <thread>
#include <cstdlib>
#include <utility>

#define DUMP_MAGIC 0x4A695444

#define DUMP_VERSION 1

#ifndef ELFMACH
#if defined(CPU_X86_64)
#define ELFMACH 62

#elif defined(CPU_X86)
#define ELFMACH 3

#elif defined(CPU_ARM32)
#define ELFMACH 40

#elif defined(CPU_ARM64)
#define ELFMACH 183

#else
#error "Could't find cpu arch."
#endif
#endif

namespace Walrus {

class PerfDump {
private:
    FILE* m_file;
    uint32_t m_pid;
    uint64_t m_codeLoadIndex;

public:
    PerfDump(bool isEnabled);
    void dumpFileHeader();
    void dumpRecordHeader(const uint32_t recordType, const uint32_t entrySize);
    void dumpCodeLoad(const uint64_t vma, const uint64_t codeAddr, const uint64_t codeSize, const std::string& functionName, const uint8_t* nativeCode);
    void dumpCodeMove(const uint64_t vma, const uint64_t oldCodeAddr, const uint64_t newCodeAddr, const uint64_t codeSize, const uint64_t codeIndex);
    void dumpCodeClose();
    ~PerfDump();
};


} // namespace Walrus
#endif
#endif
