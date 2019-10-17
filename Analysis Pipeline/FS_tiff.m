
function FS_tiff(videodata,varargin)
  % FS_tiff

  %   Create multipage Tiff stack from the .mov files form the FreedomScope

  %   Created: 2016/02/12
  %   By: WALIII
  %   Updated: 2016/02/15
  %   By: WALIII

  % FS_BatchDff_TM will do several things:
  %
  %   1. Create a grayscale mtif, called 'G.tif'
  %   2. Creates a RGB mtif, called 'RGB.tif'
  %
  %

  

  filename = 'G';
format_switch = 1;
  nparams=length(varargin);

% if mod(nparams,2)>0
% 	error('Parameters must be specified as parameter/value pairs');
% end
for i=1:2:nparams
	switch lower(varargin{i})
		case 'colors'
			colors=varargin{i+1};
            
        case 's_smooth'
            a=varargin{i+1};
			for i = 1: size(files,3)
                files(:,:,i) = wiener2(files(:,:,i),[a a]);
            end
            
        case 't_smooth'
			b=varargin{i+1};
                files = convn(files, single(reshape([1 1 1] / b, 1, 1, [])), 'same');
        case 'fname'
            filename=varargin{i+1};
        case 'format'
            format_switch=varargin{i+1};
        end
                     
    end


if format_switch == 1;
[files, n] = FS_Format(videodata,1);
else 
    files = videodata;
end
  
% if rm_artifacts ==1;
%     

% d = files2;
% files2 = ((d-min(d(:))) ./ (max(d(:)-min(d(:)))))*255;

% % scale data
% files = normalize(files,'range',[0,1])*255;
% maxV = max(files(:));
% minV = min(files(:));
%files   = (files - min(files(:))) / (max(files(:)) - min(files(:)))*255;

% Normalize data:
%files = mat2gray(files)*256;

imwrite(uint8(files(:,:,1)),[filename,'.tif']);
if size(size(videodata),2) ==4
imwrite(uint8(videodata(:,:,:,1)),[filename,'_','RGB.tif']);
end

%imwrite(bitshift(uint16(files(:,:,1)), 8),'G_16.tif');


for i=2:size(files,3) %number of images to be read
    
    K = files(:,:,i);
%     K = wiener2(K,[5 5]);
if size(size(videodata),2) ==4

    K2 = videodata(:,:,:,i);
end
    %G  = filter2(fspecial('average',3),files2(:,:,i));
    %GG = medfilt2(G);

imwrite(uint8(K),[filename,'.tif'],'WriteMode','append');
if size(size(videodata),2) ==4

imwrite(uint8(K2),[filename,'_','RGB.tif'],'WriteMode','append');
end
end

end
