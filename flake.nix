{
  description = "Exchange project.";

  inputs.nixpkgs.url = "github:nixos/nixpkgs";
  inputs.flake-utils.url = "github:numtide/flake-utils";


  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [
            (import ./nix/clang.nix)
            (import ./nix/protobuf.nix)
          ];
        };

        python3 = pkgs.python3.withPackages (p: with p; [
          protobuf
        ]);

        shell = pkgs.mkShell rec {
          name = "exchange";
          shellHook = ''
            generate_protos() {
              protoc --proto_path=protos/defs --cpp_out=protos/src protos/defs/meng.proto
            }

            generate_test_protos() {
              protoc --proto_path=protos/defs --python_out=meng/test protos/defs/meng.proto
            }

            link_compile_commands() {
              rm compile_commands.json
              ln -s `pwd`/build/compile_commands.json `pwd`/compile_commands.json
            }
          '';
          buildInputs = with pkgs; [
            protobuf3_21
            clang
            lldb
            clang-tools
            asio
            cmake
            cppcheck
            # include-what-you-use
          ] ++ [
            python3
          ];
        };
      in {
        devShells.default = shell;
      }
    );
}
