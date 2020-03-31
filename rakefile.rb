require 'rake'
require 'rake/clean'

################################################################################
# The sample code directory
dir_sampleCode = "SampleCode"
dir_outDir = "FormattedCode"

################################################################################
desc "Format Sample Code"
task :format_sample_code

directory dir_outDir
CLOBBER.include dir_outDir

sample_files = FileList[
    "SampleCode/*.cpp",
    "SampleCode/*.h",
    "SampleCode/*.c",
    "SampleCode/private/*.c",
    "SampleCode/private/*.cpp",
    "SampleCode/private/*.h",
]

sample_files.each do |src|
    dest = src.pathmap("%{^SampleCode,FormattedCode}p")
    destdir = dest.pathmap("%d")
    directory destdir
    file dest => [".clang-format", destdir, src] do
        sh "clang-format #{src} > #{dest}"
    end
    task :format_sample_code => dest

    CLOBBER.include dest
end

################################################################################
desc "Format with each style"
task :each_style

styles = ["LLVM", "Google", "Chromium", "Mozilla", "WebKit"]
sample_files.each do |src|
    styles.each do |stl|
        dest = src.pathmap("%{^SampleCode,FormattedCode}X_#{stl}%x")
        destdir = dest.pathmap("%d")
        directory destdir
        file dest => [destdir, src] do
            sh "clang-format --style=#{stl} #{src} > #{dest}"
        end
        task :each_style => dest
        CLOBBER.include dest
    end

end

################################################################################
desc "Default Task"
task :default => [dir_outDir, :format_sample_code, :each_style]
