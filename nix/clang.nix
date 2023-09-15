final: prev:
rec {
  llvm = prev.llvm_15;
  llvmPackages = prev.llvmPackages_15;
  clangStdenv = llvmPackages.libcxxStdenv;
  clang-tools = prev.clang-tools.override { inherit llvmPackages; };
  lldb = llvmPackages.lldb;
}
