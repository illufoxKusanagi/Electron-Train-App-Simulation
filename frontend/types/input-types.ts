import { Control } from "react-hook-form";

export interface InputType {
  label: string;
  unit?: string;
  type: "field" | "dropdown" | "upload" | "field-upload";
  name: string;
  value?: number | string;
  isReadOnly?: boolean;
  placeholder?: string;
  options?: string[]; // For dropdown
  requiredColumns?: number; // For CSV upload
}

export interface InputFieldProps {
  label: string;
  unit?: string;
  name: string;
  value?: number;
  placeholder?: string;
  isReadOnly?: boolean;
  control: Control<any>;
}

export interface InputDropdownProps {
  label: string;
  name: string;
  options: string[];
  value?: string | number;
  onChange?: (value: string | number) => void;
}

export interface InputUploadProps {
  label: string;
  name: string;
  requiredColumns?: number;
  targetColumns?: number[];
  onFileLoad?: (filePath: string, data: number[][]) => void;
  onError?: (error: string) => void;
}

export interface InputFieldUploadProps {
  label: string;
  unit?: string;
  name: string;
  value?: number;
  requiredColumns?: number;
  placeholder?: string;
  isReadOnly?: boolean;
  onFieldChange?: (value: number) => void;
  onFileLoad?: (filePath: string, data: number[][]) => void;
  onError?: (error: string) => void;
}
