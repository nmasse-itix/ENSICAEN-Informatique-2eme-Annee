function e = algo1(samples)
%ALGO1(samples) beat detection (algo1).

nSamples = length(samples)
blockSize = 1024
winSize = 43
nBlocks = floor(nSamples / blockSize)

instantEnergies = zeros(1, nBlocks);
localAverageEnergies = zeros(1, nBlocks);

for b = 1 : nBlocks
	for s = (b - 1) * blockSize + 1: b * blockSize
		instantEnergies(b) = instantEnergies(b) + samples(s) * samples(s);
	end
end

e = instantEnergies;
