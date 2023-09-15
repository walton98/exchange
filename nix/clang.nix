final: prev:
{
  llvm = prev.llvm_14;
  llvmPackages = prev.llvmPackages_14;
  clangStdenv = llvmPackages.libcxxStdenv;
  clang-tools = prev.clang-tools.override { inherit llvmPackages; };
  # clang = llvmPackages.
  # lldb = llvmPackages.lldb;
}
